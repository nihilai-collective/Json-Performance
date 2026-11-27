
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 879.08 | 0.127726 | 580.192ms | 5094 | 80 | 3985.76 | 5526.25 | 0.340445 | 2.7936 | 1(Win) | true |
| Jsonifier (two-stage) | 777.283 | 0.136502 | 675.972ms | 5094 | 80 | 5822.78 | 6250 | 0.040016 | 3.1636 | 2(Loss) | true |
| Glaze | 611.36 | 0.276156 | 841.981ms | 5094 | 1280 | 616374 | 7946.25 | 0.159527 | 4.03382 | 3(Loss) | true |
| simdjson (ondemand) | 427.633 | 0.145069 | 1195.71ms | 5094 | 4890 | 1.3281e+06 | 11360.2 | 0.0552327 | 5.76526 | 4(Loss) | true |
