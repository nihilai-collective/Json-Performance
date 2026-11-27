
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1832.44 | 0.135156 | 8541.74ms | 5212421 | 40 | 5.37713e+08 | 2.71274e+06 | 0.412677 | 1.35097 | 1(Win) | true |
| simdjson (ondemand) | 1710.36 | 0.142676 | 9013.88ms | 5212421 | 80 | 1.37563e+09 | 2.90639e+06 | 0.276695 | 1.44749 | 2(Loss) | true |
