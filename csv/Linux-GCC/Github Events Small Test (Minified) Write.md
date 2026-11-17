
----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8541.77 | 0.0679464 | 751.328ms | 1996 | 1280 | 29.3473 | 222.85 | 0.0910657 | 0.703762 | 1.46693 | 0.248998 | 0.000501002 | 4.34463e-05 | 1.56563e-05 | 1(Win) | true |
| simdjson (reflection) | 6464.98 | 0.0841181 | 759.032ms | 1996 | 80 | 4.90744 | 294.438 | 0.0637213 | 0.89127 | 1.87926 | 0.273547 | 0.000507265 | 2.50501e-05 | 0 | 2(Loss) | true |
| Glaze | 5279.12 | 0.12623 | 761.126ms | 1996 | 2560 | 530.352 | 360.578 | 0.213177 | 1.0671 | 3.45541 | 0.568637 | 0.000748959 | 3.44439e-05 | 1.0568e-05 | 3(Loss) | true |
