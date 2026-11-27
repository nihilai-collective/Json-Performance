
----
### Marine IK Reverse Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 751.003 | 0.427232 | 1315.26ms | 4604 | 160 | 99823.8 | 5846.47 | 0.010796 | 6.76792 | 25.447 | 5.64444 | 0.00513005 | 6.51607e-05 | 1.76477e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 674.273 | 0.329697 | 1396.23ms | 4604 | 160 | 73748 | 6511.78 | 0.0662781 | 7.54136 | 30.2871 | 6.30083 | 0.00714596 | 0.000147969 | 8.9596e-05 | 2(Loss) | true |
| Glaze | 640.294 | 0.0697319 | 1427.63ms | 4604 | 2560 | 58534.9 | 6857.34 | 0.134648 | 7.97206 | 33.9711 | 6.91985 | 0.00549183 | 7.22028e-05 | 3.10532e-05 | 3(Loss) | true |
| simdjson (ondemand) | 497.19 | 0.205121 | 1623.1ms | 4604 | 320 | 105001 | 8831.07 | 0.00729014 | 10.2064 | 40.5404 | 7.21742 | 0.00652761 | 0.000192088 | 0.000107244 | 4(Loss) | true |
