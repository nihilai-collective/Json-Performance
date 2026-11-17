
----
### Github Events Small Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13095.1 | 0.0985191 | 17.2224ms | 1996 | 1280 | 26.2516 | 145.363 | 0.393883 | 0.151564 | 1(Win) | true |
| simdjson (reflection) | 9412.22 | 0.0546007 | 23.1632ms | 1996 | 4890 | 59.6269 | 202.241 | 0.205774 | 0.225617 | 2(Loss) | true |
| Glaze | 5458.65 | 0.179631 | 38.5181ms | 1996 | 160 | 62.782 | 348.719 | 0.0663582 | 0.416082 | 3(Loss) | true |
