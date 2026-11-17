
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2847.24 | 0.563322 | 8316.31ms | 7351818 | 160 | 3.07877e+10 | 2.46247e+06 | 2.17173 | 0.869546 | 1(Win) | true |
| Jsonifier | 2730.24 | 0.104841 | 8853.12ms | 7351818 | 40 | 2.89941e+08 | 2.56799e+06 | 0.435343 | 0.9068 | 2(Loss) | true |
| simdjson (reflection) | 2427.12 | 0.322365 | 9564.47ms | 7351818 | 40 | 3.46865e+09 | 2.8887e+06 | 0.0172118 | 1.02004 | 3(Loss) | true |
| Glaze | 2184.4 | 0.166683 | 5158.3ms | 7351818 | 80 | 2.28981e+09 | 3.20968e+06 | 0.0297478 | 1.1334 | 4(Loss) | true |
| simdjson (ondemand) | 2173.6 | 0.129504 | 5171.9ms | 7351818 | 80 | 1.39601e+09 | 3.22564e+06 | 0.348294 | 1.13903 | 5(Loss) | true |
