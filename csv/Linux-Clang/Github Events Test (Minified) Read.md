
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1798.99 | 0.0635991 | 2843.29ms | 53331 | 4890 | 1.58092e+06 | 28271.6 | 0.131901 | 1.37494 | 1(Win) | true |
| Jsonifier | 1746.93 | 0.0913193 | 2917.93ms | 53331 | 2560 | 1.80957e+06 | 29114.2 | 0.0324948 | 1.41598 | 2(Loss) | true |
| Glaze | 1469.59 | 0.0748769 | 3485.96ms | 53331 | 2560 | 1.71912e+06 | 34608.7 | 0.314163 | 1.68338 | 3(Loss) | true |
| simdjson (ondemand) | 1012.47 | 0.0524378 | 5005.22ms | 53331 | 2560 | 1.77633e+06 | 50233.9 | 0.187571 | 2.44393 | 4(Loss) | true |
