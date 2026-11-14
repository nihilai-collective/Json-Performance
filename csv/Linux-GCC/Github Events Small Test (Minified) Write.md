
----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8630.36 | 0.170491 | 744.295ms | 1996 | 80 | 11.3125 | 220.562 | 0.243103 | 0.705029 | 1.46693 | 0.248998 | 0.000507265 | 1.25251e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6710.43 | 0.0391273 | 755.468ms | 1996 | 1280 | 15.7685 | 283.668 | 0.168006 | 0.878466 | 1.87926 | 0.273547 | 0.000502568 | 3.36611e-05 | 7.43675e-06 | 2(Loss) | true |
| Glaze | 5355.14 | 0.262309 | 761.418ms | 1996 | 320 | 278.199 | 355.459 | 0.277914 | 1.07398 | 3.45541 | 0.568637 | 0.000501002 | 2.50501e-05 | 1.56563e-06 | 3(Loss) | true |
