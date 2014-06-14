# Description:
#   A simple watering alert with the built in HTTP Daemon
#
# Dependencies:
#   None
#
# Configuration:
#   None
#
# Commands:
#   None
#
# URLS:
#   /hubot/plant0/moisture: SENEN NO KI - gifted from CyberAgent Ventures
#

PLEASE_WATER_VALUE = 100

module.exports = (robot) ->
  robot.router.post '/hubot/plant0/moisture', (req, res) ->
    moisture = req.body.moisture
    if moisture?
      if moisture < PLEASE_WATER_VALUE
        robot.messageRoom process.env.HUBOT_HIPCHAT_ROOMS, "青年の樹にお水をあげてー！"
      res.end 'ok'
    else
      res.end 'ng'

