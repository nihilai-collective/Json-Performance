
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1213.48 | 0.253746 | 4159.27ms | 53331 | 640 | 7.23884e+06 | 41912.7 | 0.883699 | 2.0388 | 1(Win) | true |
| simdjson (ondemand) | 995.701 | 0.0612875 | 5193.81ms | 53331 | 2560 | 2.50891e+06 | 51080 | 0.693906 | 2.48509 | 2(Loss) | true |
