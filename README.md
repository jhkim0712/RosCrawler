# ROS Crawler

STM32F407VET6 기반 Hiwonder RRC Lite Controller 보드를 사용한 ROS 플랫폼 크롤러 제어 프로젝트

## 📋 프로젝트 개요

본 프로젝트는 Hiwonder사의 RRC Lite Controller 보드(STM32F407VET6)를 기반으로 ROS(Robot Operating System) 플랫폼에서 동작하도록 구현된 크롤러 로봇 제어 시스템입니다.

## 🛠 하드웨어 사양

- **MCU**: STM32F407VET6 (ARM Cortex-M4F, 168MHz)
- **RAM**: 192KB SRAM
- **Flash**: 512KB
- **Controller Board**: Hiwonder RRC Lite Controller
- **RTOS**: FreeRTOS

## 📁 프로젝트 구조

```
RosCrawler/
├── Core/                           # STM32 Core 파일들
│   ├── Inc/                        # 헤더 파일들
│   ├── Src/                        # 소스 파일들
│   └── Startup/                    # 시작 코드
├── Drivers/                        # STM32 HAL 드라이버
│   ├── CMSIS/                      # ARM CMSIS 라이브러리
│   └── STM32F4xx_HAL_Driver/       # STM32F4 HAL 드라이버
├── Hiwonder/                       # Hiwonder 전용 라이브러리
│   ├── Chassis/                    # 섀시 제어 (차동/메카넘)
│   ├── Misc/                       # 유틸리티 함수들
│   ├── Peripherals/                # 주변 장치 드라이버
│   ├── Portings/                   # 포팅 레이어
│   ├── System/                     # 시스템 레벨 함수
│   └── USB_HOST/                   # USB 호스트 기능
├── Middlewares/                    # 미들웨어 (FreeRTOS)
└── Debug/                          # 빌드 출력물
```

## 🚀 주요 기능

### 섀시 제어
- **차동 구동 섀시** (Differential Drive)
- **메카넘 휠 섀시** (Mecanum Wheel)
- 속도 및 방향 제어
- PID 제어기 구현

### 센서 지원
- **IMU**: QMI8658 (가속도계, 자이로스코프)
- **엔코더**: 모터 엔코더 피드백
- **버튼/키**: 사용자 입력
- **LED**: 상태 표시

### 통신
- **UART**: 시리얼 통신
- **I2C**: 센서 통신
- **SPI**: 고속 통신
- **USB**: 호스트 기능

### 제어 장치
- **PWM 서보**: 서보 모터 제어
- **시리얼 서보**: Hiwonder 시리얼 서보
- **엔코더 모터**: DC 모터 + 엔코더
- **부저**: 오디오 피드백

## 🔧 개발 환경

- **IDE**: STM32CubeIDE
- **HAL Version**: STM32F4xx HAL Driver
- **RTOS**: FreeRTOS
- **Compiler**: ARM GCC
- **Debugger**: ST-Link

## 📦 의존성

- STM32F4xx HAL Driver
- FreeRTOS (CMSIS-RTOS v2)
- ARM CMSIS
- Hiwonder Hardware Library

## 🔨 빌드 방법

1. **STM32CubeIDE 설치**
   - STM32CubeIDE 최신 버전 다운로드 및 설치

2. **프로젝트 임포트**
   ```bash
   git clone https://github.com/jhkim0712/RosCrawler.git
   ```

3. **STM32CubeIDE에서 프로젝트 열기**
   - File → Open Projects from File System
   - RosCrawler 폴더 선택

4. **빌드**
   - Project → Build Project (Ctrl+B)

5. **플래시**
   - Run → Debug (F11) 또는 Run (Ctrl+F11)

## 🔗 ROS 연동

본 프로젝트는 ROS 플랫폼과의 연동을 위해 다음과 같은 기능을 제공합니다:

- **토픽 발행**: 센서 데이터 (IMU, 엔코더)
- **토픽 구독**: 제어 명령 (속도, 방향)
- **서비스**: 설정 변경, 상태 조회
- **액션**: 복잡한 동작 시퀀스

## 📊 성능 특성

- **제어 주기**: 50Hz (20ms)
- **센서 샘플링**: 100Hz (10ms)
- **통신 속도**: 115200 bps (UART)
- **최대 속도**: 설정 가능
- **정밀도**: 엔코더 기반 위치 제어

## 🛡 안전 기능

- **배터리 모니터링**: 저전압 감지
- **과전류 보호**: 모터 보호
- **비상 정지**: 하드웨어 버튼
- **타임아웃**: 통신 단절 시 안전 정지

## 📖 사용법

### 기본 동작
1. 전원 연결 및 부팅
2. ROS 노드와 시리얼 연결
3. 제어 명령 송신
4. 센서 데이터 수신 및 모니터링

### 설정
- `global_conf.h`: 전역 설정
- `motors_param.h`: 모터 파라미터
- `packet_reports.h`: 통신 프로토콜

## 🐛 문제 해결

### 일반적인 문제
1. **컴파일 에러**: 경로 설정 및 라이브러리 확인
2. **플래시 실패**: ST-Link 드라이버 설치 확인
3. **통신 문제**: 보드율 및 케이블 연결 확인

### 디버깅
- STM32CubeIDE 디버거 사용
- 시리얼 모니터로 로그 확인
- LED 상태로 시스템 상태 파악

## 🤝 기여

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 라이선스

이 프로젝트는 MIT 라이선스 하에 배포됩니다. 자세한 내용은 `LICENSE` 파일을 참조하세요.

## 📞 연락처

- **개발자**: jhkim0712
- **GitHub**: [https://github.com/jhkim0712](https://github.com/jhkim0712)
- **프로젝트 링크**: [https://github.com/jhkim0712/RosCrawler](https://github.com/jhkim0712/RosCrawler)

## 🙏 감사의 말

- Hiwonder사의 하드웨어 라이브러리 제공
- STMicroelectronics의 HAL 라이브러리
- FreeRTOS 커뮤니티
- ROS 커뮤니티

---

**Note**: 이 프로젝트는 교육 및 연구 목적으로 개발되었습니다.
