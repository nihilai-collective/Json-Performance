
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 27087.6 | 0.0432726 | 7965.07ms | 2251027 | 4890 | 5.75117e+06 | 79252.1 | 0.17139 | 0.0913685 | 1(Win) | true |
| simdjson (stage-1) | 17183.1 | 0.130329 | 6497.3ms | 2251027 | 320 | 8.48378e+06 | 124934 | 0.0748708 | 0.14405 | 2(Loss) | true |
