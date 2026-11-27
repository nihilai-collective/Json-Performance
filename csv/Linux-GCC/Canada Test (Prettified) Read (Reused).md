
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2213.28 | 0.151546 | 8440.02ms | 5212421 | 30 | 3.4755e+08 | 2.24597e+06 | 0.339093 | 1.11858 | 1(Win) | true |
| simdjson (ondemand) | 2013.66 | 0.222304 | 9140.27ms | 5212421 | 80 | 2.4093e+09 | 2.46862e+06 | 0.535692 | 1.22948 | 2(Loss) | true |
