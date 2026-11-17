
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2541.54 | 0.0505675 | 794.945ms | 1691 | 1280 | 131.779 | 634.522 | 0.199118 | 2.11887 | 7.37138 | 1.06919 | 0.00118273 | 3.78844e-05 | 3.23403e-06 | 1(Win) | true |
| Glaze | 2424.12 | 0.0648173 | 800.452ms | 1691 | 4890 | 909.222 | 665.257 | 0.0215885 | 2.22007 | 8.57363 | 1.60201 | 0.00113061 | 4.83735e-05 | 9.55377e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2094.01 | 0.0399595 | 817.201ms | 1691 | 1280 | 121.221 | 770.131 | 0.189139 | 2.54342 | 8.90834 | 1.27853 | 0.000591366 | 4.85105e-05 | 9.24009e-07 | 3(Loss) | true |
| simdjson (reflection) | 2013.46 | 0.131321 | 819.247ms | 1691 | 640 | 708.025 | 800.941 | 0.0765311 | 2.64239 | 9.01419 | 1.40686 | 0.000884277 | 5.82126e-05 | 6.46807e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1814.72 | 0.079944 | 828.662ms | 1691 | 4890 | 2468.03 | 888.658 | 0.028501 | 2.92386 | 9.27322 | 1.3702 | 0.00101633 | 6.13134e-05 | 1.48749e-05 | 5(Loss) | true |
