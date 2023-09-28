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

        stage('Deploy'){
            steps {
                sh "docker-compose -f docker-compose.yml up -d --build"
            }
        }
    }
}
//docker run -it --rm --name loto loto:latest