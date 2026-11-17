
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1755.2 | 0.0422619 | 1367.84ms | 11812 | 1280 | 9416.77 | 6417.95 | 0.0345469 | 2.9486 | 14.0227 | 2.64265 | 0.00826397 | 1.06486e-05 | 1.32281e-07 | 1(Win) | true |
| simdjson (ondemand) | 1581.71 | 0.0495934 | 1439.41ms | 11812 | 640 | 7984 | 7121.9 | 0.098429 | 3.27406 | 14.6178 | 2.41763 | 0.0069667 | 9.52421e-06 | 7.93684e-07 | 2(Loss) | true |
