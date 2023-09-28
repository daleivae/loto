pipeline {
    agent any

    environment {
        DATE = new Date().format('yy.M')
    }
    stages {
        stage('Build') {
            steps {
                sh "docker build -t loto ."
            }
        }
    }
}
//docker run -it --rm --name loto loto:latest