
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1635.16 | 0.0450476 | 303.505ms | 4215 | 160 | 196.219 | 2458.32 | 0.0404403 | 1(Win) | true |
| Glaze | 1018.36 | 0.188685 | 458.243ms | 4215 | 640 | 35501.4 | 3947.25 | 0.828081 | 2(Loss) | true |
| simdjson (ondemand) | 852.272 | 0.20438 | 588.854ms | 4215 | 640 | 59469.8 | 4716.5 | 0.108841 | 3(Loss) | true |
