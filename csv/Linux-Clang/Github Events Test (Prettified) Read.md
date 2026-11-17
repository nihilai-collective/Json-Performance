
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 23681.8 | 0.0255623 | 266.609ms | 65103 | 160 | 71.861 | 2621.72 | 0.00143034 | 0.103534 | 1(Win) | true |
| simdjson (stage-1) | 21585 | 0.0369554 | 292.938ms | 65103 | 80 | 90.3949 | 2876.4 | 0.0929118 | 0.113659 | 2(Loss) | true |
