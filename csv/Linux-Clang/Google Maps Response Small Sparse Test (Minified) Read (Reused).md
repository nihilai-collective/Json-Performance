
----
### Google Maps Response Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2252.76 | 0.0604504 | 907.877ms | 4390 | 1280 | 1615.51 | 1858.45 | 0.0385758 | 2.33557 | 10.4009 | 1.8959 | 0.00205634 | 2.50925e-05 | 1.24573e-06 | 1(Win) | true |
| simdjson (ondemand) | 1955.54 | 0.0251742 | 932.722ms | 4390 | 4890 | 1420.42 | 2140.91 | 0.00930684 | 2.68246 | 11.574 | 1.82961 | 0.00263529 | 1.97046e-05 | 5.91603e-06 | 2(Loss) | true |
