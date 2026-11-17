
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1188.26 | 0.0234004 | 4528.85ms | 56369 | 4890 | 548043 | 45240.7 | 0.0142766 | 2.55631 | 1(Win) | true |
| Glaze | 1061.89 | 0.0332536 | 5069.32ms | 56369 | 4890 | 1.38581e+06 | 50624.3 | 0.0628886 | 2.86082 | 2(Loss) | true |
| Jsonifier (two-stage) | 968.369 | 0.0475096 | 5543.67ms | 56369 | 1280 | 890370 | 55513.6 | 0.00281471 | 3.13734 | 3(Loss) | true |
| simdjson (ondemand) | 700.974 | 0.204944 | 7692.35ms | 56369 | 160 | 3.95248e+06 | 76690 | 0.122395 | 4.33471 | 4(Loss) | true |
