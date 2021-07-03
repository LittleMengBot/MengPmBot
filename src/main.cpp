#include "blacklist/blacklist.h"
#include "utils/strtools.h"
#include <exception>
#include <tgbot/tgbot.h>
using namespace TgBot;

void forward_message(Bot &bot, int64_t &admin_id, BlackListDb &db) {
    bot.getEvents().onAnyMessage([&bot, &admin_id, &db](const Message::Ptr& message) {
        if (message->chat->type != TgBot::Chat::Type::Private) return;

        if (message->text.starts_with("/r")) {
            if (message->chat->id == admin_id) {
                try {
                    std::string reply_text = parse_text(message->text);
                    if (reply_text.empty()) {
                        bot.getApi().sendMessage(admin_id, "reply_text required!", false, message->messageId);return;
                    }
                    int64_t receiver_id = strtoll(parse_id(message->text).c_str(), nullptr, 0);
                    bot.getApi().sendMessage(receiver_id, "[reply]\n" + reply_text);
                    bot.getApi().sendMessage(admin_id, "Success!", false, message->messageId);
                } catch (std::exception &e) {
                    bot.getApi().sendMessage(admin_id, e.what(), false, message->messageId);
                    std::cout<<e.what()<<std::endl;
                }
                return;
            }else return;

        }

        if (message->text.starts_with("/ban") && message->text != "/banlist") {
            if (message->text.ends_with("/ban")) {
                bot.getApi().sendMessage(admin_id, "user_id && name required!", false, message->messageId);return;
            }
            if (message->chat->id == admin_id) {
                try {
                    int64_t ban_id = strtoll(parse_id(message->text).c_str(), nullptr, 0);
                    std::string ban_name = parse_text(message->text);
                    if (!db.check_blacklist(ban_id)) {
                        db.add_blacklist(ban_id, ban_name);
                        bot.getApi().sendMessage(admin_id, "Ban Success!", false, message->messageId);
                    } else {
                        bot.getApi().sendMessage(admin_id, "Already Banned!", false, message->messageId);
                    }
                } catch (std::exception &e) {
                    bot.getApi().sendMessage(admin_id, e.what());
                    std::cout<<e.what()<<std::endl;
                }
                return;
            }else return;
        }

        if (message->text.starts_with("/unban")) {
            if (message->text.ends_with("/unban")) {
                bot.getApi().sendMessage(admin_id, "user_id expected!");return;
            }
            if (message->chat->id == admin_id) {
                try {
                    int64_t unban_id = strtoll(parse_id(message->text).c_str(), nullptr, 0);
                    if (db.check_blacklist(unban_id)) {
                        db.delete_blacklist(unban_id);
                        bot.getApi().sendMessage(admin_id, "Unban Success!", false, message->messageId);
                    } else {
                        bot.getApi().sendMessage(admin_id, "Not in blacklist!", false, message->messageId);
                    }
                } catch (std::exception &e) {
                    bot.getApi().sendMessage(admin_id, e.what());
                    std::cout<<e.what()<<std::endl;
                }
                return;
            }else return;
        }

        if (message->text.starts_with("/banlist")) {
            if (message->chat->id == admin_id) {
                try {
                    std::string reply_text = db.get_blacklist();
                    bot.getApi().sendMessage(admin_id, reply_text, false, message->messageId);
                } catch (std::exception &e) {
                    bot.getApi().sendMessage(admin_id, e.what(), false, message->messageId);
                    std::cout<<e.what()<<std::endl;
                }
                return;
            }else return;
        }

        if (message->text == "/help" || message->text == "/start") {
            bot.getApi().sendMessage(message->chat->id, "Please send message directly.");return;
        }

        if (db.check_blacklist(message->chat->id)) {
            bot.getApi().sendMessage(message->chat->id, "You are banned!", false, message->messageId);return;
        } else if (message->chat->id == admin_id){
            bot.getApi().sendMessage(message->chat->id, "Not required.", false, message->messageId);return;
        } else {
            bot.getApi().forwardMessage(admin_id, message->chat->id, message->messageId);
            bot.getApi().sendMessage(message->chat->id, "Success!", false, message->messageId);
            std::string mark("user_id:\n");
            mark.append("<code>" + std::to_string(message->chat->id) + "</code>");
            mark.append("\n");
            mark.append("<code>" + message->chat->firstName + message->chat->lastName + "</code>");
            bot.getApi().sendMessage(admin_id, mark, false, 0, nullptr, "HTML");
            return;
        }
    });
}
int main() {
    std::string token("1234567890:Aaaaaaaaaa");  //Place your token here.
    Bot bot = Bot(token);
    int64_t admin_id = 1234567890;  //Place your id here.
    BlackListDb db = init_db();

    try {
        forward_message(bot, admin_id, db);
        TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (std::exception &e) {
        bot.getApi().sendMessage(admin_id, e.what());
        std::cout<<e.what()<<std::endl;
    }

    return EXIT_SUCCESS;
}
