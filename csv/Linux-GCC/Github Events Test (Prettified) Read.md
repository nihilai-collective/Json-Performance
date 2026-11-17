
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 2224.66 | 0.0792971 | 2791.64ms | 65103 | 4890 | 2.39496e+06 | 27908.5 | 0.0197917 | 1.11177 | 1(Win) | true |
| Jsonifier (two-stage) | 2037.48 | 0.156722 | 3122.71ms | 65103 | 1280 | 2.91932e+06 | 30472.4 | 0.00593739 | 1.21396 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1773.29 | 0.205701 | 3545.2ms | 65103 | 320 | 1.65984e+06 | 35012.3 | 0.018604 | 1.39501 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 1755.45 | 0.514037 | 3650.57ms | 65103 | 160 | 5.28853e+06 | 35368.2 | 0.174401 | 1.40888 | 3(Tie) | true |
| simdjson (ondemand) | 1556.86 | 0.13418 | 4049.51ms | 65103 | 1280 | 3.66513e+06 | 39879.6 | 0.654085 | 1.58913 | 5(Loss) | true |
