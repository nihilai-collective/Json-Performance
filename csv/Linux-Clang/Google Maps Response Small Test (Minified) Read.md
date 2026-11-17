
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1291.65 | 0.0250205 | 1046.07ms | 4390 | 4890 | 3216.21 | 3241.32 | 0.230669 | 4.03628 | 18.0189 | 3.50228 | 0.00231284 | 6.82905e-05 | 2.0776e-05 | 1(Win) | true |
| simdjson (ondemand) | 1059.33 | 0.039373 | 1137.38ms | 4390 | 2560 | 6198.8 | 3952.16 | 0.0640654 | 4.90895 | 20.5497 | 3.56173 | 0.00263374 | 4.27107e-05 | 1.27242e-05 | 2(Loss) | true |
