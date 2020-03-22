const fs = require("fs")

const {
  asyncReadFile,
  asyncWriteFile
} = require('./dao')

exports.getTask = async (req, res) => {
  const id = req.params.id
  const file = await asyncReadFile(req.app.locals.dataFilePath)
  const tasks = JSON.parse(file).filter(v => v.id === id)
  tasks.length == 0 ? res.status(404).send() : res.send(tasks[0])
}

exports.getAllTasks = (req, res) => fs.readFile(req.app.locals.dataFilePath, "utf-8", (err, data) => {
  if (err) {
    return res.status(500).send()
  }
  res.send(JSON.parse(data))
})

exports.createTask = async (req, res) => {
  const newTask = req.body
  console.log(req.body)
  const file = await asyncReadFile(req.app.locals.dataFilePath)
  const tasks = JSON.parse(file)
  if (tasks.filter(v => v.id === newTask.id).length != 0) {
    res.status(400).send()
  } else {
    tasks.push(newTask)
    await asyncWriteFile(JSON.stringify(tasks), req.app.locals.dataFilePath)
    res.status(201).send(tasks)
  }
}

exports.deleteTask = async (req, res) => {
  const id = req.params.id
  const file = await asyncReadFile(req.app.locals.dataFilePath)
  const tasks = JSON.parse(file)
  const newTasks = tasks.filter(v => v.id !== id)
  if (newTasks.length === tasks.length) {
    res.status(404).send()
  } else {
    await asyncWriteFile(JSON.stringify(newTasks), req.app.locals.dataFilePath)
    console.log(newTasks)
    res.status(204).send(newTasks)
  }
}
