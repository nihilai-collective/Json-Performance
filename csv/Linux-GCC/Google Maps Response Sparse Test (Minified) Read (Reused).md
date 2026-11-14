
----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2509.65 | 0.105371 | 1176.76ms | 11812 | 640 | 14316.8 | 4488.6 | 0.00222781 | 2.06731 | 10.3176 | 1.79961 | 0.00256122 | 1.01856e-05 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 2060.82 | 0.0254554 | 1273.55ms | 11812 | 4890 | 9467.48 | 5466.17 | 0.0965068 | 2.51631 | 11.1641 | 1.85354 | 0.0040262 | 3.14401e-05 | 1.31577e-05 | 2(Loss) | true |
