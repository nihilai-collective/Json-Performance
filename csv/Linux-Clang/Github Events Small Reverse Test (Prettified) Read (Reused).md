
----
### Github Events Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1195.06 | 0.176317 | 900.867ms | 2158 | 80 | 737.569 | 1722.11 | 0.0980862 | 4.41355 | 15.7247 | 3.17933 | 0.00185357 | 9.26784e-05 | 2.8962e-05 | 1(Win) | true |
| simdjson (ondemand) | 944.494 | 0.153455 | 957.826ms | 2158 | 80 | 894.455 | 2178.97 | 0.339599 | 5.55649 | 22.443 | 3.89342 | 0.00161608 | 3.47544e-05 | 0 | 2(Loss) | true |
