
----
### Twitter Test (Prettified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21616.1 | 0.280542 | 2792.41ms | 631514 | 2560 | 1.56404e+07 | 27861.6 | 0.658743 | 0.114422 | 1(Win) | true |
| simdjson (stage-1) | 19491.5 | 0.0618753 | 3071.2ms | 631514 | 4890 | 1.78738e+06 | 30898.5 | 0.192068 | 0.126908 | 2(Loss) | true |
