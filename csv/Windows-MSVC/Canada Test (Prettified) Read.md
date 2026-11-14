
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16238.7 | 0.302638 | 8007.22ms | 5373214 | 1280 | 1.16741e+09 | 315560 | 0.425354 | 0.187061 | 1(Win) | true |
| simdjson (stage-1) | 12716.6 | 0.606799 | 5129.33ms | 5373214 | 640 | 3.82647e+09 | 402962 | 1.61271 | 0.238904 | 2(Loss) | true |
