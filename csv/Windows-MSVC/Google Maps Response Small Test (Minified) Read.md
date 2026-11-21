
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1189.17 | 0.301401 | 369.398ms | 4390 | 2560 | 288250 | 3520.62 | 0.122198 | 2.06461 | 1(Win) | true |
| Jsonifier (two-stage) | 1029.5 | 0.319277 | 419.945ms | 4390 | 30 | 5057.47 | 4066.67 | 0.0820345 | 2.38358 | 2(Loss) | true |
| Glaze | 819.042 | 0.191528 | 525.061ms | 4390 | 4890 | 468693 | 5111.62 | 0.157179 | 3.00636 | 3(Loss) | true |
| simdjson (ondemand) | 594.956 | 0.622737 | 809.877ms | 4390 | 160 | 307248 | 7036.88 | 0.0443892 | 4.14521 | 4(Loss) | true |
