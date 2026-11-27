
----
### CitmCatalog Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3274.79 | 0.0425891 | 864.231ms | 5092 | 4890 | 1950.37 | 1482.88 | 0.0550244 | 1.61285 | 7.48885 | 1.36765 | 0.0036011 | 1.42973e-05 | 3.8956e-06 | 1(Win) | true |
| simdjson (ondemand) | 2974.1 | 0.0541305 | 882.97ms | 5092 | 2560 | 1999.82 | 1632.8 | 0.462922 | 1.78406 | 8.21426 | 1.28869 | 0.00248444 | 1.99455e-05 | 8.97548e-06 | 2(Loss) | true |
