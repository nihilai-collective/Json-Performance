
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22864.9 | 0.106803 | 2651.74ms | 631514 | 1280 | 1.01299e+06 | 26339.9 | 0.0182415 | 0.108171 | 1(Win) | true |
| simdjson (stage-1) | 20710.5 | 0.0811998 | 2905.12ms | 631514 | 4890 | 2.72649e+06 | 29079.9 | 0.0512388 | 0.119431 | 2(Loss) | true |
