
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 960.916 | 0.073025 | 1267.41ms | 4630 | 1280 | 14412.7 | 4595.11 | 0.0511322 | 5.43638 | 26.5881 | 4.65443 | 0.00259905 | 4.08342e-05 | 7.25567e-06 | 1(Win) | true |
| Jsonifier (generic) | 838.791 | 0.0799696 | 1332.44ms | 4630 | 640 | 11341.9 | 5264.14 | 0.140891 | 6.24777 | 26.8687 | 5.34341 | 0.00945937 | 1.88985e-05 | 3.37473e-07 | 2(Loss) | true |
