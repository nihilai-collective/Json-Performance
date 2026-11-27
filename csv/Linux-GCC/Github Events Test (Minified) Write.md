
----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12716.5 | 0.140047 | 444.821ms | 58581 | 30 | 1135.65 | 4393.27 | 0.00834541 | 0.193421 | 1(Win) | true |
| simdjson (reflection) | 10335.7 | 0.0663478 | 534.292ms | 58581 | 80 | 1028.92 | 5405.29 | 0.104868 | 0.238291 | 2(Loss) | true |
| Glaze | 6636.69 | 0.151109 | 846.84ms | 58581 | 2560 | 414220 | 8417.93 | 0.379609 | 0.371823 | 3(Loss) | true |
