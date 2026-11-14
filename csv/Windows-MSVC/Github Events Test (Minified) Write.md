
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11531.9 | 0.0987608 | 487.377ms | 58581 | 4890 | 111941 | 4844.58 | 0.135052 | 0.261818 | 1(Win) | true |
| Glaze | 5210.92 | 0.266973 | 1086.07ms | 58581 | 1280 | 1.04864e+06 | 10721.2 | 0.37082 | 0.581866 | 2(Loss) | true |
