
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1816.79 | 0.324261 | 624.323ms | 11812 | 1280 | 517415 | 6200.4 | 0.10955 | 1(Win) | true |
| Jsonifier (two-stage) | 1206.52 | 0.144425 | 941.295ms | 11812 | 4890 | 889145 | 9336.62 | 0.0757901 | 2(Loss) | true |
| simdjson (reflection) | 1012.34 | 0.514236 | 1206.39ms | 11812 | 30 | 98228.7 | 11127.5 | 0.539707 | 3(Loss) | true |
| Glaze | 965.775 | 0.535322 | 1197.47ms | 11812 | 320 | 1.2476e+06 | 11664 | 0.565595 | 4(Loss) | true |
| simdjson (ondemand) | 685.44 | 0.32393 | 1700.42ms | 11812 | 640 | 1.8138e+06 | 16434.4 | 0.696089 | 5(Loss) | true |
