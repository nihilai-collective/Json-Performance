
----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14178.7 | 0.0667028 | 1137.01ms | 58581 | 320 | 2210.44 | 3940.22 | 7.93104e-05 | 0.360456 | 1.09925 | 0.163193 | 3.39274e-05 | 3.81416e-05 | 2.38985e-05 | 1(Win) | true |
| simdjson (reflection) | 11654.9 | 0.0718203 | 1222.1ms | 58581 | 1280 | 15170.5 | 4793.45 | 0.0181922 | 0.437018 | 1.47317 | 0.205545 | 3.39941e-05 | 4.67302e-05 | 2.95798e-05 | 2(Loss) | true |
| Glaze | 8625.55 | 0.152373 | 1387.41ms | 58581 | 1280 | 124671 | 6476.94 | 0.0695859 | 0.591877 | 2.36218 | 0.354176 | 3.30205e-05 | 1.88841e-05 | 1.03889e-05 | 3(Loss) | true |
