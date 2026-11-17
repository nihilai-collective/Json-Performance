
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16895.1 | 0.0379063 | 7750.54ms | 5373214 | 1280 | 1.69192e+07 | 303301 | 0.0684607 | 0.179818 | 1(Win) | true |
| simdjson (stage-1) | 13057.7 | 0.0411878 | 9981.89ms | 5373214 | 160 | 4.18017e+06 | 392436 | 0.0508303 | 0.232697 | 2(Loss) | true |
