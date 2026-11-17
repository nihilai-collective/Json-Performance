
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1132.64 | 0.0768865 | 1192.59ms | 4604 | 160 | 1421.38 | 3876.55 | 0.0706668 | 4.59738 | 19.4513 | 4.19699 | 0.00278426 | 4.34405e-05 | 5.43006e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 924.978 | 0.069991 | 1282.6ms | 4604 | 1280 | 14128.7 | 4746.83 | 0.0393015 | 5.58561 | 23.8999 | 4.62055 | 0.00240314 | 5.54884e-05 | 1.03511e-05 | 2(Loss) | true |
| Glaze | 738.969 | 0.0534415 | 1406.81ms | 4604 | 2560 | 25811.7 | 5941.68 | 0.287187 | 6.98067 | 29.5996 | 5.9627 | 0.00574628 | 4.15739e-05 | 1.84113e-05 | 3(Loss) | true |
| simdjson (reflection) | 696.078 | 0.0378757 | 1448.8ms | 4604 | 4890 | 27911.6 | 6307.79 | 0.00960768 | 7.37958 | 27.0766 | 5.066 | 0.00832138 | 0.0001838 | 0.000113665 | 4(Loss) | true |
| simdjson (ondemand) | 537.679 | 0.0577023 | 1652.56ms | 4604 | 1280 | 28419.8 | 8166.06 | 0.0904319 | 9.61562 | 33.1201 | 6.65408 | 0.0147577 | 0.000142878 | 7.12695e-05 | 5(Loss) | true |
