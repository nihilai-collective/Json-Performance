
----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4461.87 | 0.0453106 | 1275.18ms | 25388 | 1280 | 7738.05 | 5426.39 | 0.0113293 | 1.16256 | 5.61005 | 0.888845 | 0.00135143 | 5.07745e-06 | 2.46179e-07 | 1(Win) | true |
| simdjson (ondemand) | 4072.64 | 0.0439417 | 1324.05ms | 25388 | 1280 | 8735.14 | 5945.01 | 0.00428387 | 1.27258 | 5.89794 | 0.891287 | 0.00145683 | 1.33552e-05 | 8.924e-07 | 2(Loss) | true |
