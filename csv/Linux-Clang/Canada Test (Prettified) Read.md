
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23298.9 | 0.0959274 | 5616.27ms | 5373214 | 320 | 1.42441e+07 | 219938 | 0.0338078 | 0.106248 | 1(Win) | true |
| simdjson (stage-1) | 20458 | 0.0782179 | 6397.2ms | 5373214 | 1280 | 4.91321e+07 | 250479 | 0.0202801 | 0.121005 | 2(Loss) | true |
