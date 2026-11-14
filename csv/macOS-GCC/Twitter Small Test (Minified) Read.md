
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2140.27 | 0.782195 | 133.2ms | 2889 | 2560 | 259555 | 1287.3 | 1.67278 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1763.91 | 0.698067 | 161.989ms | 2889 | 4890 | 581361 | 1561.97 | 0.308497 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1744.33 | 0.670365 | 159.782ms | 2889 | 2560 | 287013 | 1579.5 | 0.643558 | 2(Tie) | true |
| simdjson (reflection) | 1205.13 | 0.661702 | 221.866ms | 2889 | 1280 | 292930 | 2286.2 | 1.20138 | 4(Loss) | true |
| simdjson (ondemand) | 1055.3 | 0.775763 | 273.182ms | 2889 | 640 | 262534 | 2610.8 | 0.291948 | 5(Loss) | true |
