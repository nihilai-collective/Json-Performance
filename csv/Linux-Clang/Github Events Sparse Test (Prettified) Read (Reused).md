
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8860.12 | 0.0419168 | 1444.32ms | 65103 | 1280 | 11043.5 | 7007.47 | 0.131094 | 0.584499 | 2.69333 | 0.329063 | 0.000685752 | 3.07206e-06 | 4.20008e-07 | 1(Win) | true |
| simdjson (ondemand) | 8284.01 | 0.0783751 | 1496ms | 65103 | 160 | 5520.74 | 7494.81 | 0.0194339 | 0.625118 | 2.8522 | 0.323011 | 0.000776942 | 2.59205e-06 | 4.80009e-07 | 2(Loss) | true |
