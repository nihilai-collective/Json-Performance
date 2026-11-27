
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1198.02 | 0.166051 | 6335.16ms | 5212421 | 30 | 1.42414e+09 | 4.1493e+06 | 0.366719 | 1(Win) | true |
| simdjson (ondemand) | 1142.86 | 0.19639 | 6548.4ms | 5212421 | 80 | 5.83746e+09 | 4.34959e+06 | 0.194288 | 2(Loss) | true |
