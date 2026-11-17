
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 970.159 | 0.0436835 | 457.792ms | 4604 | 160 | 625.374 | 4525.77 | 0.0354786 | 2.53686 | 1(Win) | true |
| Jsonifier (two-stage) | 828.592 | 0.299651 | 533.75ms | 4604 | 1280 | 322724 | 5299.01 | 0.25664 | 2.97326 | 2(Loss) | true |
| Glaze | 698.146 | 0.107713 | 630.739ms | 4604 | 4890 | 224399 | 6289.11 | 0.145201 | 3.53167 | 3(Loss) | true |
| simdjson (reflection) | 667.699 | 0.12639 | 662.083ms | 4604 | 4890 | 337788 | 6575.89 | 0.0415723 | 3.69327 | 4(Loss) | true |
| simdjson (ondemand) | 544.799 | 0.175621 | 819.119ms | 4604 | 30 | 6009.95 | 8059.33 | 0.0458884 | 4.53094 | 5(Loss) | true |
