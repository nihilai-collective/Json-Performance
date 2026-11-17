
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15031.3 | 0.0540808 | 1113.25ms | 58581 | 4890 | 19756.7 | 3716.71 | 0.193625 | 0.338858 | 1.04838 | 0.165549 | 3.4427e-05 | 2.40696e-05 | 1.43266e-05 | 1(Win) | true |
| simdjson (reflection) | 11089.6 | 0.0499647 | 1251.69ms | 58581 | 4890 | 30982.4 | 5037.79 | 0.00222303 | 0.45628 | 1.4875 | 0.210171 | 5.15602e-05 | 2.84925e-05 | 1.63792e-05 | 2(Loss) | true |
| Glaze | 8565.92 | 0.149655 | 1396.28ms | 58581 | 1280 | 121944 | 6522.03 | 0.122872 | 0.593333 | 2.36218 | 0.354176 | 3.52743e-05 | 4.8824e-05 | 3.066e-05 | 3(Loss) | true |
