
----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4961.5 | 0.0347776 | 2812.31ms | 108313 | 1280 | 67103.4 | 20819.4 | 0.0254056 | 1.03555 | 5.35389 | 0.803671 | 0.000664877 | 2.20715e-06 | 1.87535e-07 | 1(Win) | true |
| simdjson (ondemand) | 4418.5 | 0.0243455 | 3074.99ms | 108313 | 4890 | 158401 | 23377.9 | 0.104966 | 1.16557 | 5.91343 | 0.721012 | 0.00146751 | 2.13726e-06 | 4.45577e-07 | 2(Loss) | true |
