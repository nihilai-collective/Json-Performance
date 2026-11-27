
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2902.53 | 0.0957318 | 2765.24ms | 83958 | 2560 | 1.78535e+06 | 27585.8 | 3.5401e-05 | 0.852158 | 1(Win) | true |
| Jsonifier (two-stage) | 2723.14 | 0.112261 | 2949.57ms | 83958 | 1280 | 1.39461e+06 | 29403.1 | 0.0950872 | 0.908338 | 2(Loss) | true |
| Glaze | 1961.61 | 0.064321 | 4091.52ms | 83958 | 4890 | 3.37066e+06 | 40817.9 | 0.062542 | 1.26131 | 3(Loss) | true |
| simdjson (ondemand) | 1200.66 | 0.0854505 | 6671.83ms | 83958 | 1280 | 4.15646e+06 | 66687.1 | 0.120336 | 2.06121 | 4(Loss) | true |
