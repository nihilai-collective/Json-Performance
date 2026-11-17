
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1173.3 | 0.096311 | 359.25ms | 4390 | 4890 | 57753 | 3568.26 | 0.0268123 | 2.57497 | 1(Win) | true |
| Jsonifier (two-stage) | 1013.48 | 0.14777 | 418.79ms | 4390 | 320 | 11923.9 | 4130.94 | 0.0529261 | 2.9866 | 2(Loss) | true |
| Glaze | 882.296 | 0.172199 | 478.592ms | 4390 | 640 | 42730.8 | 4745.16 | 0.0691017 | 3.43088 | 3(Loss) | true |
| simdjson (ondemand) | 542.837 | 0.148181 | 784.408ms | 4390 | 40 | 5224.36 | 7712.5 | 0.0108038 | 5.58191 | 4(Loss) | true |
