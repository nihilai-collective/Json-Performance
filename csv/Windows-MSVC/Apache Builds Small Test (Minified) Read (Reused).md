
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1699.3 | 0.100998 | 182.053ms | 2632 | 4890 | 10883.5 | 1477.12 | 0.144752 | 1.7662 | 1(Win) | true |
| Jsonifier | 1680.51 | 0.131843 | 179.618ms | 2632 | 4890 | 18963.4 | 1493.64 | 0.275967 | 1.77989 | 2(Loss) | true |
| Glaze | 1603.32 | 0.865327 | 190.834ms | 2632 | 1280 | 234911 | 1565.55 | 0.233994 | 1.87171 | 3(Loss) | true |
| simdjson (ondemand) | 1212.78 | 1.80546 | 248.418ms | 2632 | 320 | 446821 | 2069.69 | 1.02196 | 2.47958 | 4(Loss) | true |
