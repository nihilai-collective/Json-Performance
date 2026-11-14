
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21751 | 0.160843 | 6032.29ms | 5373214 | 160 | 2.2974e+07 | 235589 | 0.0398629 | 0.113809 | 1(Win) | true |
| simdjson (stage-1) | 19186.7 | 0.0621739 | 6856.94ms | 5373214 | 1280 | 3.52935e+07 | 267075 | 0.577526 | 0.129024 | 2(Loss) | true |
