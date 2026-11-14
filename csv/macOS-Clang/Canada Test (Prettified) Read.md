
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8035.55 | 0.175575 | 8249.09ms | 5373214 | 30 | 3.76084e+07 | 637703 | 0.167394 | 1(Win) | true |
| simdjson (stage-1) | 6942.13 | 0.327755 | 9788.97ms | 5373214 | 30 | 1.75591e+08 | 738144 | 0.176795 | 2(Loss) | true |
