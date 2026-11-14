
----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7952.47 | 0.131647 | 6580.14ms | 2090234 | 40 | 4.3558e+06 | 250665 | 0.0831682 | 0.636896 | 3.25146 | 0.398855 | 0.00262987 | 0.0508313 | 3.40871e-06 | 1(Win) | true |
| simdjson (ondemand) | 7254.74 | 0.0574914 | 7254.44ms | 2090234 | 30 | 748639 | 274772 | 0.0922216 | 0.709285 | 3.65775 | 0.418386 | 0.00240045 | 0.0496593 | 2.07313e-07 | 2(Loss) | true |
