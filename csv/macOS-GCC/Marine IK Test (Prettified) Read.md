
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1985.6 | 0.337796 | 5125.71ms | 7351818 | 40 | 5.69082e+09 | 3.53105e+06 | 0.21227 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1658.46 | 0.492665 | 6831.14ms | 7351818 | 40 | 1.73517e+10 | 4.22755e+06 | 3.72079 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1623.46 | 1.02814 | 6118.67ms | 7351818 | 30 | 5.91472e+10 | 4.3187e+06 | 0.155944 | 2(Tie) | true |
| simdjson (ondemand) | 1466.14 | 0.32962 | 7350.1ms | 7351818 | 30 | 7.45392e+09 | 4.7821e+06 | 0.249021 | 4(Loss) | true |
| Glaze | 1371.43 | 1.17281 | 7663.17ms | 7351818 | 40 | 1.43801e+11 | 5.11237e+06 | 2.81975 | 5(Loss) | true |
