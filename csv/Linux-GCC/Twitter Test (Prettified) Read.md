
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19602.4 | 0.156192 | 3130.48ms | 631514 | 1280 | 2.94764e+06 | 30723.8 | 0.024384 | 0.126189 | 1(Win) | true |
| simdjson (stage-1) | 16247.8 | 0.0775914 | 3803.07ms | 631514 | 2560 | 2.1176e+06 | 37067.1 | 0.143397 | 0.152265 | 2(Loss) | true |
