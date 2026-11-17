
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2151.46 | 0.200107 | 8589.56ms | 5212421 | 30 | 6.41297e+08 | 2.3105e+06 | 0.519879 | 1.15075 | 1(Win) | true |
| simdjson (ondemand) | 1968.95 | 0.11654 | 9458.06ms | 5212421 | 30 | 2.59706e+08 | 2.52467e+06 | 0.00752762 | 1.25741 | 2(Loss) | true |
