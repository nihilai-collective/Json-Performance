
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2822.02 | 0.0810759 | 1595.26ms | 25388 | 1280 | 61934.2 | 8579.63 | 0.106333 | 1.83201 | 8.79355 | 1.56113 | 0.0019081 | 2.47718e-05 | 1.26782e-05 | 1(Win) | true |
| simdjson (ondemand) | 2250.07 | 0.0360945 | 1819.42ms | 25388 | 4890 | 73765.9 | 10760.5 | 0.104306 | 2.28242 | 9.62222 | 1.69787 | 0.00364382 | 3.07779e-05 | 1.85183e-05 | 2(Loss) | true |
