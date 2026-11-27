
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2508.89 | 0.0777756 | 7060.62ms | 360584 | 1280 | 1.45461e+07 | 137064 | 0.151973 | 0.986515 | 1(Win) | true |
| Jsonifier (generic) | 2393.26 | 0.07793 | 7474.72ms | 360584 | 2560 | 3.20983e+07 | 143687 | 0.499835 | 1.03419 | 2(Loss) | true |
